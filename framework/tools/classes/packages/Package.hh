<?hh // strict

class Package {

	public static function parse(Source $source, string $package): ?Package {
		$s = explode(' ', $package);
		if (count($s) >= 3) {
			return new Package($source, $s[0], $s[1], $s[2]);
		} else {
			return null;
		}
	}
	
	protected Source $_source;
	protected string $_name;
	protected string $_channel;
	protected string $_url;

	public function __construct(Source $source, string $name, string $channel, string $url) {
		$this->_source = $source;
		$this->_name = $name;
		$this->_channel = $channel;
		$this->_url = $url;
	}

	/******************* Properties *******************/

	public function source(): Source {
		return $this->_source;
	}

	public function name(): string {
		return $this->_name;
	}

	public function channel(): string {
		return $this->_channel;
	}

	public function url(): string {
		return $this->_url;
	}

	/***************** Dynamic Properties ***************/

	public function archiveURL(): string {
		return str_replace('{CHANNEL}', $this->channel(), $this->url());
	}

	public function path(): string {
		return MangoSystem::system()->libraryHome().'/'.$this->name();
	}

	public function pathForVersion(Version $version): string {
		return $this->path().'/'.$version->shortVersionString();
	}

	public function isInstalled(): bool {
		return file_exists($this->path());
	}

	public function isVersionInstalled(Version $version): bool {
		foreach ($this->installedVersions() as $installedVersion) {
			if ($installedVersion->isEqualTo($installedVersion)) {
				return true;
			}
		}
		return false;
	}

	public function installedVersions(): Vector<Version> {
		$installedVersions = new Vector(null);
		if (file_exists($this->path())) {
			$entries = scandir($this->path());
			foreach ($entries as $entry) {
				if ($entry != '.' && $entry != '..') {
					$path = $this->path().'/'.$entry;
					if (is_dir($path)) {
						$version = Version::parseFromFilesInPath($path);
						if ($version != null) {
							$installedVersions->add($version);
						}
					}
				}
			}
		}
		return $installedVersions;
	}

	/**************** Protected Methods *****************/

	protected function archivePath(): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$this->channel().'.zip';
	}

	protected function packagePath(): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$this->channel();
	}

	/**************** Methods *****************/

	public function install(): void {
		if (!file_exists($this->packagePath())) {
			if (!file_exists($this->archivePath())) {
				if (!FileManager::downloadFile($this->archiveURL(), $this->archivePath())) {
					throw new Exception("Failed to download library package from '".$this->archiveURL()."'");
				}
			}
			
			if (!FileManager::extractPackage($this->archivePath(), $this->packagePath())) {
				throw new Exception("Failed to extract library package from '".$this->archivePath()."' to '".$this->path()."'");
			}
		}
		
		$version = Version::parseFromFilesInPath($this->packagePath());
		if ($version != null) {
			//
		} else {
			throw new Exception("Package at '".$this->packagePath()."' appears to be corrupted");
		}
	}

	public function uninstallVersion(Version $version): void {
		//
	}

	public function uninstall(): void {
		//
	}

}

