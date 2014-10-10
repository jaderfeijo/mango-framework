<?hh // strict

class PackageManager {
	
	protected static PackageManager $_sharedManager = new PackageManager();

	public static function sharedManager(): PackageManager {
		return self::$_sharedManager;
	}
	
	protected string $_temporaryPath;

	protected Vector<Source> $_sources;

	public function __construct() {
		$this->_temporaryPath = '/var/tmp/mango-pkg-manager';

		$this->_sources = new Vector(null);
		$file = fopen(MangoSystem::system()->frameworkHome().'/SOURCES', 'r');
		while (!feof($file)) {
			$source = Source::parse(fgets($file));
			if ($source != null) {
				$this->_sources->add($source);
			}
		}
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
		return $this->_sources;
	}

	/***************** Methods ********************/

	public function packageNamed(string $name): ?Package {
		foreach ($this->sources() as $source) {
			$package = $source->packageNamed($name);
			if ($package != null) {
				return $package;
			}
		}
		return null;
	}

}

