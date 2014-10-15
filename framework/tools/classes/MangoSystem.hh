<?hh // strict

class MangoSystem {

	const string MANGO_HOME = '/usr/lib/mango';
	const string MANGO_FRAMEWORK_FOLDER = 'framework';
	const string MANGO_LIBRARY_FOLDER = 'library';

	protected static ?MangoSystem $_system = null;

	public static function system() : MangoSystem {
		if (self::$_system == null) {
			self::$_system = new MangoSystem();
		}
		return self::$_system;
	}

	public function __construct() {
		//
	}

	/**************** Dynamic Properties *****************/

	public function home() : string {
		return MangoSystem::MANGO_HOME;
	}

	public function frameworkHome() : string {
		return MangoSystem::MANGO_HOME.'/'.MangoSystem::MANGO_FRAMEWORK_FOLDER;
	}

	public function libraryHome() : string {
		return MangoSystem::MANGO_HOME.'/'.MangoSystem::MANGO_LIBRARY_FOLDER;
	}
	
	public function version() : Version {
		$version = Version::parseFromFilesInPath(self::MANGO_HOME.'/'.self::MANGO_FRAMEWORK_FOLDER);
		if ($version == null) {
			throw new Exception('An error occured while parsing the system version');
		}
		return $version;
	}

}

