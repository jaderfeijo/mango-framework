<?hh // strict

class MangoProjectVersionDecrementCommand extends Command {
	
	public function __construct() {
		parent::__construct('decrement', 'decrements the current project version', Vector {'change'});
	}
	
	public function execute(Vector<string> $args) : int {
		return 0;
	}
	
}
