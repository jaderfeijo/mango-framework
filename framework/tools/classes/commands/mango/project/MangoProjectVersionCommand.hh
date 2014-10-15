<?hh // strict

class MangoProjectVersionCommand extends CommandCollection {
	
	public function __construct() {
		parent::__construct('version');
		
		$this->addCommand(new MangoProjectVersionSetCommand());
		$this->addCommand(new MangoProjectVersionIncrementCommand());
		$this->addCommand(new MangoProjectVersionDecrementCommand());
	}
	
}

