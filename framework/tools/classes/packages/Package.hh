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

	protected function archiveURL(string $channel): string {
		return str_replace('{CHANNEL}', $channel, $this->url());
	}

	protected function archivePath(string $channel): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel.'.zip';
	}

	protected function packagePath(string $channel): string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel;
	}

	/**************** Methods *****************/

	public function archiveURLForVersion(?Version $version): string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->archiveURL($channel);
	}

	public function archivePathForVersion(?Version $version): string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->archivePath($channel);
	}

	public function packagePathForVersion(?Version $version): string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->packagePath($channel);
	}

	public function hasArchiveForVersion(?Version $version): bool {
		return file_exists($this->archivePathForVersion($version));
	}

	public function hasPackageForVersion(?Version $version): bool {
		return file_exists($this->packagePathForVersion($version));
	}

	public function fetch(?Version $version): void {
		if (!$this->hasArchiveForVersion($version)) {
			FileManager::downloadFile($this->archiveURLForVersion($version), $this->archivePathForVersion($version));
		}
	}

	public function extract(?Version $version): void {
		if (!$this->hasPackageForVersion($version)) {
			FileManager::extractPackage($this->archivePathForVersion($version), $this->source()->cachesPath());
		}
	}

	public function install(?Version $version): void {
		$packagePath = $this->packagePathForVersion($version);
		if (file_exists($packagePath)) {
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

				$library = PackageManager::sharedManager()->libraryNamed($this->name());
				if ($library !== null) {
					$library->updateSymbolicLinks();
				} else {
					throw new PackageException($this, PackageException::POST_INSTALLATION_ERROR);
				}
			} else {
				throw new PackageException($this, PackageException::CORRUPTED_PACKAGE_ERROR);
			}
		} else {
			throw new PackageException($this, PackageException::PACKAGE_NOT_FOUND_ERROR);
		}
	}

}

