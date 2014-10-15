<?hh // strict

class MangoCommand extends CommandCollection {
	
	public function __construct() {
		parent::__construct('mango');
		
		$this->addCommand(new MangoInfoCommand());
		$this->addCommand(new MangoUpdateCommand());
		$this->addCommand(new MangoLibraryCommand());
		$this->addCommand(new MangoProjectCommand());
		$this->addCommand(new MangoSourcesCommand());
	}
	
}

