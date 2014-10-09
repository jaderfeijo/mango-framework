<?hh // strict

class MangoLibraryCommand extends CommandCollection {
	
	public function __construct() {
		parent::__construct('library');
		
		$this->addCommand(new MangoLibraryListCommand());
		$this->addCommand(new MangoLibraryInstallCommand());
		$this->addCommand(new MangoLibraryUninstallCommand());
		$this->addCommand(new MangoLibraryUpdateCommand());
	}
	
}
