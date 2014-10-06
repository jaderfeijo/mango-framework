<?hh // strict

class MangoSystem {

	const string MANGO_INSTALLATION_PATH = '/usr/lib/mango';
	const string MANGO_LIBRARY_FOLDER_NAME = 'library';

	protected static ?MangoSystem $_system = null;

	public static function system(): MangoSystem {
		if (self::$_system === null) {
			self::$_system = new MangoSystem();
		}
		return self::$_system;
	}

	protected Project $_project;

	public function __construct() {
		$this->_project = new Project(self::MANGO_INSTALLATION_PATH);
	}

	/**************** Properties *****************/

	public function project(): Project {
		return $this->_project;
	}

}

