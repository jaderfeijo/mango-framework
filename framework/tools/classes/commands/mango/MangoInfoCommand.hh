<?hh // strict

class MangoInfoCommand extends Command {
	
	public function __construct() {
		parent::__construct('info', 'provides information about the installed version of the mango framework');
	}
	
	public function execute(Vector<string> $args): int {
		Console::stdout()->printLn('Installed Version: '.(string)MangoSystem::system()->version());
		return 0;
	}
	
}
