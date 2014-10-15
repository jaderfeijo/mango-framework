<?hh // strict

class Archive {

	protected string $_name;
	protected string $_path;

	public function __construct(string $name, string $path) {
		$this->_name = $name;
		$this->_path = $path;
	}

	/******************** Properties ********************/

	public function name() : string  {
		return $this->_name;
	}

	public function path() : string {
		return $this->_path;
	}

	/******************** Methods ********************/

	public function install() : void {
		if (file_exists($this->path())) {
			$version = Version::parseFromFilesInPath($this->path());
			if ($version !== null) {
				$library = PackageManager::sharedManager()->libraryNamed($this->name());
				if ($library !== null) {
					if ($library->isVersionInstalled($version)) {
						$library->uninstall($version);
					}
				}

				$libraryPath = Library::pathForLibrary($this->name(), $version);
				FileManager::copyDirectory($this->path(), $libraryPath);

				$library = PackageManager::sharedManager()->libraryNamed($this->name());
				if ($library !== null) {
					$library->updateSymbolicLinks();
				} else {
					throw new ArchiveException($this, ArchiveException::POST_INSTALLATION_ERROR);
				}
			} else {
				throw new ArchiveException($this, ArchiveException::CORRUPTED_ARCHIVE_ERROR);
			}
		} else {
			throw new ArchiveException($this, ArchiveException::ARCHIVE_NOT_FOUND_ERROR);
		}
	}

}
