<?hh

class Library {

	public static function pathForLibrary(string $name, ?Version $version) : string {
		if ($version != null) {
			return MangoSystem::system()->libraryHome().'/'.$name.'/'.$version->shortVersionString();
		} else {
			return MangoSystem::system()->libraryHome().'/'.$name;
		}
	}
	
	protected $_name;

	public function __construct(string $name) {
		$this->_name = $name;
	}

	/****************** Properties ******************/

	public function name() : string {
		return $this->_name;
	}

	/***************** Dynamic Properties *********************/

	public function path() : string {
		return Library::pathForLibrary($this->name(), null);
	}

	public function isInstalled() : bool {
		return file_exists($this->path());
	}

	public function installedVersions() : Vector<Version> {
		$installedVersions = new Vector(null);
		if (file_exists($this->path())) {
			$entries = scandir($this->path());
			foreach ($entries as $entry) {
				if ($entry != '.' && $entry != '..') {
					$path = $this->path().'/'.$entry;
					if (is_dir($path) && !is_link($path)) {
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

	public function latestVersion() : ?Version {
		return Version::parseFromFilesInPath($this->path().'/latest');
	}

	/****************** Protected Methods ********************/

	protected function pathForVersion(Version $version) : string {
		return Library::pathForLibrary($this->name(), $version);
	}

	/******************** Methods ********************/
	
	public function updateSymbolicLinks() : void {
		$highestVersion = null;
		foreach ($this->installedVersions() as $version) {
			if ($highestVersion != null) {
				if ($version->isGreaterThan($highestVersion)) {
					$highestVersion = $version;
				}
			} else {
				$highestVersion = $version;
			}
		}

		$latestPath = $this->path().'/latest';
		if ($highestVersion != null) {
			if (file_exists($latestPath)) {
				$latestVersion = Version::parseFromFilesInPath($latestPath);
				if ($latestVersion != null) {
					if ($highestVersion->isGreaterThan($latestVersion)) {
						unlink($latestPath);
						symlink($this->pathForVersion($highestVersion), $latestPath);
					}
				}
			} else {
				symlink($this->pathForVersion($highestVersion), $latestPath);
			}
		} else {
			if (file_exists($latestPath)) {
				unlink($latestPath);
			}
		}
	}

	public function isVersionInstalled(Version $version) : bool {
		foreach ($this->installedVersions() as $v) {
			if ($version->shortVersionString() == $v->shortVersionString()) {
				return true;
			}
		}
		return false;
	}

	public function uninstall(?Version $version) : void {
		if ($version == null) {
			FileManager::removeDirectory($this->path());
		} else {
			FileManager::removeDirectory($this->pathForVersion($version));
			if ($this->installedVersions()->count() <= 0) {
				FileManager::removeDirectory($this->path());
			} else {
				$this->updateSymbolicLinks();
			}
		}
	}

}
