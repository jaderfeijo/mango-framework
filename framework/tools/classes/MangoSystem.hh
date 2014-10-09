<?hh // strict

class MangoSystem {

	const string MANGO_INSTALLATION_PATH = '/usr/lib/mango';
	const string MANGO_LIBRARY_FOLDER_NAME = 'library';

	protected static MangoSystem $_system = new MangoSystem();

	public static function system(): MangoSystem {
		return self::$_system;
	}

	public function __construct() {
		//
	}

	/**************** Dynamic Properties *****************/
	
	public function version(): Version {
		return Version::parseFromFilesInPath(self::MANGO_INSTALLATION_PATH);
	}
}

