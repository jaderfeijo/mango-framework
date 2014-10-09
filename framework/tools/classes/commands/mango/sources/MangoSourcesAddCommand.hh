<?hh // strict

class MangoSourcesAddCommand extends Command {
	
	public function __construct() {
		parent::__construct('add', 'adds a new source to the list of available sources', Vector {'url'});
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
