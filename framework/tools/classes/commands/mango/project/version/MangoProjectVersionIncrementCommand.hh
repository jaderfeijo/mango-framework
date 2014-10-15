<?hh // strict

class MangoProjectVersionIncrementCommand extends Command {
	
	public function __construct() {
		parent::__construct('increment', 'increments the current project version', Vector {'change'});
	}
	
	public function execute(Vector<string> $args) : int {
		return 0;
	}
	
}

