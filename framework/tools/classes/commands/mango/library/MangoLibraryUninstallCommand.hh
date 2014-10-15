<?hh // strict

class MangoLibraryUninstallCommand extends Command {
	
	public function __construct() {
		parent::__construct('uninstall', 'uninstalls the specified {version} of a [library]', Vector {'library'}, Vector {'version'});
	}
	
	public function execute(Vector<string> $args) : int {
		$libraryName = $args[0];
		$version = null;
		if ($args->count() > 1) {
			$version = Version::parse($args[1]);
		}

		$success = false;
		if ($libraryName != null) {
			$library = PackageManager::sharedManager()->libraryNamed($libraryName);
			if ($library !== null) {
				if ($version !== null) {
					Console::stdout()->printLn("* Uninstalling version '".$version->shortVersionString()."' of library '".$library->name()."'...");
				} else {
					Console::stdout()->printLn("* Uninstalling all versions of library '".$library->name()."'");
				}
				$library->uninstall($version);
				Console::stdout()->printLn("* All done!");
				$success = true;
			} else {
				Console::stdout()->printLn("The library named '".$libraryName."' could not be found in your system!");
			}
		} else {
			Console::stdout()->printLn("No library name specified!");
		}

		if ($success) {
			return 0;
		} else {
			return 1;
		}
	}
	
}
