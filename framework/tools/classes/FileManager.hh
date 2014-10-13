<?hh

class FileManager {

	protected static FileManager $_sharedManager = new FileManager();

	public static function sharedManager(): FileManager {
		return self::$_sharedManager;
	}

	public static function downloadFile(string $url, string $path): bool {
		$file = fopen($path, 'w');
		$curl = curl_init($url);
		curl_setopt($curl, CURLOPT_TIMEOUT, 0);
		curl_setopt($curl, CURLOPT_FILE, $file);
		curl_setopt($curl, CURLOPT_FOLLOWLOCATION, true);
		$success = curl_exec($curl);
		curl_close($curl);
		fclose($curl);
		return $success;
	}
	
	public static function extractPackage(string $package, string $output): bool {
		$archive = new ZipArchive();
		if ($archive->open($package)) {
			$archive->extractTo($output);
			$archive->close();
			return true;
		} else {
			return false;
		}
	}
	public static function copyDirectory(string $source, string $destination): void {
		if (!file_exists($destination)) {
			mkdir($destination, 0777, true);
		}
		$dir = scandir($source);
		foreach ($dir as $f) {
			if ($f != '.' && $f != '..') {
				$sourcePath = "$source/$f";
				$destinationPath = "$destination/$f";
				if (is_dir($sourcePath)) {
					FileManager::copyDirectory($sourcePath, $destinationPath);
				} else {
					copy($sourcePath, $destinationPath);
				}
			}
		}
	}
	public static function removeDirectory(string $path): void {
		if (file_exists($path)) {
			$dir = scandir($path);
			foreach ($dir as $f) {
				if ($f != '.' && $f != '..') {
					$fullPath = "$path/$f";
					if (is_dir($fullPath)) {
						FileManager::removeDirectory($fullPath);
					} else {
						unlink($fullPath);
					}
				}
			}
			rmdir($dir);
		}
	}

	public function __construct() {
		//
	}

}

