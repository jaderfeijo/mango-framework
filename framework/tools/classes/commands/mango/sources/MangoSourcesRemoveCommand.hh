<?hh // strict

class MangoSourcesRemoveCommand extends Command {
	
	public function __construct() {
		parent::__construct('remove', 'removes a source from the list of available sources', Vector {'url'});
	}
	
	public function execute(Vector<string> $args) : int {
		return 0;
	}
	
}

