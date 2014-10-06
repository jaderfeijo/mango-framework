<?hh // strict

class MangoSourcesCommand extends CommandCollection {
	
	public function __construct() {
		parent::__construct('sources');
		
		$this->addCommand(new MangoSourcesListCommand());
		$this->addCommand(new MangoSourcesAddCommand());
		$this->addCommand(new MangoSourcesRemoveCommand());
	}
	
}
