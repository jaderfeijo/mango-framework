<?hh // strict

class MangoLibraryInstallCommand extends Command {
	
	public function __construct() {
		parent::__construct('install', 'installs the specified [{source}:library] with the specified {version}', Vector {'source:library'}, Vector {'version'});
	}
	
	public function execute(Vector<string> $args): int {
		$sourceLibrary = new Vector(explode(':', $args[0]));
		$sourceName = 'main';
		$libraryName = null;
		if ($sourceLibrary->count() >= 2) {
			$sourceName = $sourceLibrary[0];
			$libraryName = $sourceLibrary[1];
		} else {
			$libraryName = $args[0];
		}

		$version = null;
		if ($args->count() > 1) {
			$version = Version::parse($args[1]);
		}
		
		$success = false;
		if ($libraryName != null) {
			$source = PackageManager::sharedManager()->sourceNamed($sourceName);
			if ($source != null) {
				Console::stdout()->printLn("* Fetching libraries for source '".$sourceName."'");
				$source->fetch();

				$package = $source->packageNamed($libraryName);
				if ($package != null) {
					try {
						Console::stdout()->printLn("* Downloading latest version of library '".$libraryName."' from '".$package->archiveURLForVersion($version)."'");
						$package->fetch($version);

						Console::stdout()->printLn("* Extracting package...");
						$package->extract($version);

						Console::stdout()->printLn("* Installing library...");
						$package->install($version);

						$success = true;
					} catch (Exception $e) {
						Console::stdout()->printException($e);
					}
				} else {
					Console::stdout()->printLn("Could not find package for library named '".$libraryName."'!");
				}
			} else {
				Console::stdout()->printLn("Could not find source named '".$sourceName."'!");
			}
		} else {
			Console::stdout()->printLn("Error parsing library name!");
		}

		Console::stdout()->printLn("* Cleaning up...");
		PackageManager::sharedManager()->clearCache();

		if ($success) {
			return 0;
		} else {
			return 1;
		}
	}
	
}

