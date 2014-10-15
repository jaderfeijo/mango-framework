<?hh

class ArchiveException extends Exception {

	const int CORRUPTED_ARCHIVE_ERROR = 1000;
	const int ARCHIVE_NOT_FOUND_ERROR = 1001;
	const int POST_INSTALLATION_ERROR = 1002;

	public function __construct(Archive $archive, int $reason) {
		$message = "Unknown error with archive '".$archive->name()."' at path '".$archive->path()."'!";
		if ($reason == PackageException::CORRUPTED_ARCHIVE_ERROR) {
			$message = "The installation archive '".$archive->name()."' at path '".$archive->path()."' appears to be corrupted!";
		} else if ($reason == PackageException::ARCHIVE_NOT_FOUND_ERROR) {
			$message = "The installation archive '".$archive->name()."' at path '".$archive->path()."' could not be found!";
		} else if ($reason == PackageException::POST_INSTALLATION_ERROR) {
			$message = "A post installation error occurred when installing archive '".$archive->name()."' at path '".$archive->path()."'!";
		}
		parent::__construct($message, $reason);
	}

}
