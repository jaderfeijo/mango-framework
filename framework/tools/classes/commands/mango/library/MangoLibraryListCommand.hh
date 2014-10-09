<?hh // strict

class MangoLibraryListCommand extends Command {
	
	public function __construct() {
		parent::__construct('list', 'lists all installed libraries');
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
