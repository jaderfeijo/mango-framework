<?hh

require_once('constants.hh');
require_once('LibraryNotFoundException.hh');

class LibraryManager {

	protected static ?LibraryManager $_sharedLoader;

	public static function sharedManager() : LibraryManager {
		if (LibraryManager::$_sharedLoader === null) {
			LibraryManager::$_sharedLoader = new LibraryManager();
		}
		return LibraryManager::$_sharedLoader;
	}

	protected Map<string, string> $_libraries;

	public function __construct() {
		$this->_libraries = new Map(null);
	}

	/******************** Properties ********************/

	public function libraries() : Map<string, string> {
		return $this->_libraries;
	}

	/******************** Private Methods ********************/

	private function _pathForClass(string $className, string $path) : ?string {
		$dir = new DirectoryIterator($path);
		foreach ($dir as $fileInfo) {
			if (!$fileInfo->isDot()) {
				if ($fileInfo->isDir()) {
					$path = $this->_pathForClass($className, $fileInfo->getPathname());
					if ($path !== null) {
						return $path;
					}
				} else {
					if ($fileInfo->getExtension() == MANGO_CLASS_EXTENSION) {
						$fileClassName = basename($fileInfo->getFilename(), '.'.MANGO_CLASS_EXTENSION);
						if ($fileClassName == $className) {
							return $fileInfo->getPathname();
						}
					}
				}
			}
		}

		return null;
	}

	private function _pathForLibraryVersion(string $library, string $version) : string {
		return MANGO_LIBRARY_PATH."/$library/$version";
	}

	/******************** Methods ********************/

	public function addLibrary(string $library, string $version = MANGO_LIBRARY_DEFAULT_VERSION) : bool {
		if (!$this->containsLibrary($library)) {
			if (file_exists($this->_pathForLibraryVersion($library, $version))) {
				$this->_libraries->set($library, $version);
			} else {
				throw new LibraryNotFoundException($library, $version);
			}
			return true;
		} else {
			return false;
		}
	}

	public function versionForLibrary(string $library) : ?string {
		return $this->libraries()->get($library);
	}

	public function containsLibrary(string $library) : bool {
		return $this->libraries()->containsKey($library);
	}
	
	public function pathForLibrary(string $library) : ?string {
		$version = $this->versionForLibrary($library);
		if ($version !== null) {
			return $this->_pathForLibraryVersion($library, $version);
		} else {
			return null;
		}
	}

	public function pathForClass(string $className) : ?string {
		foreach ($this->libraries() as $library => $version) {
			$path = $this->pathForClassInLibrary($library, $className);
			if ($path !== null) {
				return $path;
			}
		}
		return null;
	}

	public function pathForClassInLibrary(string $library, string $className) : ?string {
		$path = $this->pathForLibrary($library).'/'.MANGO_CLASSES_FOLDER;
		if ($path !== null) {
			return $this->_pathForClass($className, $path);
		} else {
			return null;
		}
	}

}

