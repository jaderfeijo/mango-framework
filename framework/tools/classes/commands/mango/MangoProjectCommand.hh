<?hh // strict

class MangoProjectCommand extends CommandCollection {
	
	public function __construct() {
		parent::__construct('project');
		
		$this->addCommand(new MangoProjectInfoCommand());
		$this->addCommand(new MangoProjectVersionCommand());
	}
	
}

