<?hh // strict

class PackageManager {
	
	protected static PackageManager $_sharedManager = new PackageManager();

	public static function sharedManager(): PackageManager {
		return self::$_sharedManager;
	}
	
	protected string $_temporaryPath;
	protected Vector<Source> $_sources;
	protected Vector<Library> $_libraries;

	public function __construct() {
		$this->_temporaryPath = '/var/tmp/mango-pkg-manager';
		$this->_sources = new Vector(null);
		$this->_libraries = new Vector(null);
	}

	/******************* Properties ********************/

	public function temporaryPath(): string {
		return $this->_temporaryPath;
	}

	public function setTemporaryPath(string $temporaryPath): void {
		$this->_temporaryPath = $temporaryPath;
	}

	/****************** Dynamic Properties ******************/

	public function cachesPath(): string {
		return $this->temporaryPath().'/caches';
	}

	public function sources(): Vector<Source> {
		if ($this->_sources->isEmpty()) {
			$this->loadSources();
		}	
		return $this->_sources;
	}

	public function libraries(): Vector<Library> {
		if ($this->_libraries->isEmpty()) {
			$this->loadLibraries();
		}
		return $this->_libraries;
	}

	/***************** Protected Methods *************/

	protected function sourcesPath(): string {
		return MangoSystem::system()->frameworkHome().'/SOURCES';
	}

	protected function loadSources(): void {
		$this->sources()->clear();	
		$file = fopen($this->sourcesPath(), 'r');
		while (!feof($file)) {
			$source = Source::parse(fgets($file));
			if ($source != null) {
				$this->_sources->add($source);
			}
		}
		fclose($file);
	}

	protected function loadLibraries(): void {
		$this->libraries()->clear();
		$dir = scandir(MangoSystem::system()->libraryHome());
		foreach ($dir as $f) {
			if ($f != '.' && $f != '..') {
				$path = MangoSystem::system()->libraryHome().'/'.$f;
				if (is_dir($path)) {
					$library = new Library($f);
					$this->libraries()->add($library);
				}
			}
		}
	}

	protected function saveSources(): void {
		$file = fopen($this->sourcesPath(), 'w');
		foreach ($this->sources() as $source) {
			fwrite($file, $source->name().' '.$source->url()."\n");
		}
		fclose($file);
	}

	/***************** Methods ********************/

	public function addSource(Source $source): void {
		$this->sources()->add($source);
		$this->saveSources();
	}

	public function removeSource(Source $source): void {
		$this->sources()->removeKey($this->sources()->linearSearch($source));
		$this->saveSources();
	}

	public function sourceNamed(string $name): ?Source {
		foreach($this->sources() as $source) {
			if ($source->name() == $name) {
				return $source;
			}
		}
		return null;
	}

	public function libraryNamed(string $name): ?Library {
		foreach($this->libraries() as $library) {
			if ($library->name() == $name) {
				return $library;
			}
		}
		return null;
	}

}

