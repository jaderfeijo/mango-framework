<?hh // strict

class MangoSourcesListCommand extends Command {
	
	public function __construct() {
		parent::__construct('list', 'lists all available sources');
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
