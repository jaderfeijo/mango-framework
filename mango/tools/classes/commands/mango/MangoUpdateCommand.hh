<?hh

class MangoUpdateCommand extends Command {

	public function __construct() {
		parent::__construct('update', 'updates the current version of the mango-framework using the specified {channel}', null, Vector {'channel'});
	}

	public function mangoOnlineSource(string $branch): string {
		return "https://github.com/jaderfeijo/mango-framework/archive/$branch.zip";
	}

	public function mangoOnlineVersion(string $branch): Version {
		$versionURL = "https://raw.githubusercontent.com/jaderfeijo/mango-framework/$branch/VERSION";
		$revisionURL = "https://raw.githubusercontent.com/jaderfeijo/mango-framework/$branch/REVISION";
		$versionString = $this->getContentsOfURL($versionURL);
		$revisionString = $this->getContentsOfURL($revisionURL);
		return Version::parse($versionString.'.'.$revisionString);
	}

	public function getContentsOfURL(string $url): string {
		$curl = curl_init();
		curl_setopt($curl, CURLOPT_URL, $url);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
		$contents = curl_exec($curl);
		curl_close($curl);
		return $contents;
	}

	public function execute(Vector<string> $args): int {
		$branch = 'master';
		if ($args->count() > 0) $branch = $args[0];
		$onlineSource = $this->mangoOnlineSource($branch);
		
		Console::stdout()->printLn("Checking for updates...");
		$onlineVersion = $this->mangoOnlineVersion($branch);
		$installedVersion = MangoSystem::system()->project()->version();

		if ($installedVersion->isSmallerThan($onlineVersion)) {
			// download the mango package	
			Console::stdout()->printLn('Downloading latest version '.(string)$onlineVersion.'...');
			$tmpFolder = '/var/tmp';
			$fileName = "$branch.zip";
			file_put_contents("$tmpFolder/$fileName", fopen($onlineSource, 'r'));

			// extract package
			$extractFolder = "mango-framework-$branch";
			$zip = new ZipArchive();
			if ($zip->open("$tmpFolder/$fileName") === true) {
				$zip->extractTo($extractFolder);
				$zip->close();
			} else {
				Console::stdout()->printLn('Failed to extract update package!');
			}
		} else {
			Console::stdout()->printLn('Current version '.(string)$installedVersion.' is the latest!');
		}

		return 0;
	}

}
