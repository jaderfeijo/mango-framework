<?hh // strict

class MangoLibraryInstallCommand extends Command {
	
	public function __construct() {
		parent::__construct('install', 'installs the specified [library] with the specified [version]', Vector {'library'}, Vector {'version'});
	}
	
	public function execute(Vector<string> $args): int {
		return 0;
	}
	
}
