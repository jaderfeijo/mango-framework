<?hh // strict

class PackageManager {
	
	protected static PackageManager $_sharedManager = new PackageManager();

	public function sharedManager(): PackageManager {
		return self::$_sharedManager;
	}
	
	protected string $_temporaryPath;

	public function __construct() {
		$this->_temporaryPath = '/var/tmp/mango-pkg-manager';
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
		$file = fopen(MangoSystem::MANGO_INSTALLATION_PATH.'/SOURCES');
		while (!feof($file)) {
			$source = Source::parse(fgets($file));
		}
		return Vector { };
	}

}

