<?hh // strict

class MangoProjectInfoCommand extends Command {
	
	public function __construct() {
		parent::__construct('info', 'provides information about the current mango project');
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
