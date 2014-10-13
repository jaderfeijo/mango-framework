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

	/**************** Protected Methods *****************/

	public function archiveURL(string $channel): string {
		return str_replace('{CHANNEL}', $channel, $this->url());
	}

	protected function archivePath(string $channel): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel.'.zip';
	}

	protected function packagePath(string $channel): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel;
	}

	/**************** Methods *****************/

	public function install(?Version $version): void {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		
		$packagePath = $this->packagePath($channel);
		$archivePath = $this->archivePath($channel);
		$archiveURL = $this->archiveURL($channel);

		if (!file_exists($packagePath)) {
			if (!file_exists($archivePath)) {
				if (!FileManager::downloadFile($archiveURL, $archivePath)) {
					throw new Exception("Failed to download library package from '".$archiveURL."'");
				}
			}
			
			if (!FileManager::extractPackage($archivePath, $packagePath)) {
				throw new Exception("Failed to extract library package from '".$archivePath."' to '".$packagePath."'");
			}
		}
		
		$packageVersion = Version::parseFromFilesInPath($packagePath);
		if ($packageVersion != null) {
			$library = PackageManager::sharedManager()->libraryNamed($this->name());
			if ($library != null) {
				if ($library->isVersionInstalled($packageVersion)) {
					$library->uninstall($packageVersion);
				}
			}

			$libraryPath = Library::pathForLibrary($this->name(), $packageVersion);
			FileManager::copyDirectory($packagePath, $libraryPath);
		} else {
			throw new Exception("Package at '".$packagePath."' appears to be corrupted");
		}
	}

}

