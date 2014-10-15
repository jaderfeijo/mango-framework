<?hh // strict

class MangoLibraryUpdateCommand extends Command {
	
	public function __construct() {
		parent::__construct('update', 'updates all version of the specified [library] or all installed libraries if no [library] is specified', null, Vector {'library'});
	}
	
	public function execute(Vector<string> $args) : int {
		return 0;
	}
	
}
