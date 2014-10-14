<?hh

class FileManager {

	public static function downloadFile(string $url, string $path): void {		
		FileManager::createDirectory(dirname($path));
		$file = fopen($path, 'w');
		if ($file !== false) {
			$curl = curl_init($url);
			if ($curl !== false) {
				if (!curl_setopt($curl, CURLOPT_TIMEOUT, 0)) {
					throw new DownloadErrorException($url, DownloadErrorException::DOWNLOAD_OPT_FAILED);
				}
				if (!curl_setopt($curl, CURLOPT_FILE, $file)) {
					throw new DownloadErrorException($url, DownloadErrorException::DOWNLOAD_OPT_FAILED);
				}
				if (!curl_setopt($curl, CURLOPT_FOLLOWLOCATION, true)) {
					throw new DownloadErrorException($url, DownloadErroException::DOWNLOAD_OPT_FAILED);
				}
				if (!curl_exec($curl)) {
					throw new DownloadErroException($url, DownloadErrorException::DOWNLOAD_FAILED);
				}
				curl_close($curl);
				if (!fclose($file)) {
					throw new FileException($path, FileException::CLOSING_ERROR);
				}
			} else {
				throw new DownloadErrorException($url, DownloadErrorException::DOWNLOAD_INIT_FAILED);
			}
		} else {
			throw new FileException($path, FileException::OPENING_ERROR);
		}
	}
	
	public static function extractPackage(string $package, string $output): void {
		$archive = new ZipArchive();
		if (!$archive->open($package)) {
			throw new ZipFileException($package, $output, ZipFileException::OPENING_ERROR);
		}
		if (!$archive->extractTo($output)) {
			throw new ZipFileException($package, $output, ZipFileException::EXTRACTION_ERROR);
		}
		if (!$archive->close()) {
			throw new ZipFileException($package, $output, ZipFileException::CLOSING_ERROR);
		}
	}

	public static function copyDirectory(string $source, string $destination): void {
		if (!file_exists($destination)) {
			FileManager::createDirectory($destination);
		}
		$dir = scandir($source);
		if ($dir !== false) {
			foreach ($dir as $f) {
				if ($f != '.' && $f != '..') {
					$sourcePath = "$source/$f";
					$destinationPath = "$destination/$f";
					if (is_dir($sourcePath)) {
						FileManager::copyDirectory($sourcePath, $destinationPath);
					} else {
						FileManager::copyFile($sourcePath, $destinationPath);
					}
				}
			}
		} else {
			throw new DirectoryException($source, DirectoryException::READ_ERROR);
		}
	}

	public static function removeDirectory(string $path): void {
		if (file_exists($path)) {
			$dir = scandir($path);
			if ($dir !== false) {
				foreach ($dir as $f) {
					if ($f != '.' && $f != '..') {
						$fullPath = "$path/$f";
						if (is_dir($fullPath)) {
							FileManager::removeDirectory($fullPath);
						} else {
							FileManager::removeFile($fullPath);
						}
					}
				}
				if (!rmdir($path)) {
					throw new DirectoryException($path, DirectoryException::REMOVE_ERROR);
				}
			} else {
				throw new DirectoryException($path, DirectoryException::READ_ERROR);
			}
		}
	}

	public static function copyFile(string $source, string $destination): void {
		if (!copy($source, $destination)) {
			throw new FileException("$source --> $destination", FileException::COPY_ERROR);
		}
	}

	public static function removeFile(string $path): void {
		if (!unlink($path)) {
			throw new FileException($path, FileException::REMOVE_ERROR);
		}
	}

	public static function createDirectory(string $path): void {
		if (!file_exists($path)) {
			if (!mkdir($path, 0777, true)) {
				throw new DirectoryException($path, DirectoryException::CREATE_ERROR);
			}
		}
	}

}

