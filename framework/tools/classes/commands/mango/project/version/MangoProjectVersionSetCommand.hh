<?hh // strict

class MangoProjectVersionSetCommand extends Command {
	
	public function __construct() {
		parent::__construct('set', 'sets the current project version to the specified [version]', Vector {'version'});
	}
	
	public function execute(Vector<string> $args) : int {
		return 0;
	}
	
}

