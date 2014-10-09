<?hh // strict

class MangoLibraryUninstallCommand extends Command {
	
	public function __construct() {
		parent::__construct('uninstall', 'uninstalls the specified [version] of a [library]', Vector {'library'}, Vector {'version'});
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
