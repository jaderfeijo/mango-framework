<?hh

class FileException extends Exception {

	const int OPENING_ERROR = 1000;
	const int CLOSING_ERROR = 1001;
	const int COPY_ERROR = 1002;
	const int REMOVE_ERROR = 1003;
	const int FILE_NOT_OPEN_ERROR = 1004;
	const int FILE_ALREADY_OPEN_ERROR = 1005;
	const int READ_ERROR = 1006;

	public function __construct(string $path, int $reason) {
		$message = "Unknown file error for file at path '".$path."'";
		if ($reason == FileException::OPENING_ERROR) {
			$message = "Failed to open file at path '".$path."'";
		} else if ($reason == FileException::CLOSING_ERROR) {
			$message = "Failed to close file at path '".$path."'";
		} else if ($reason == FileException::COPY_ERROR) {
			$message = "Failed to copy file at path '".$path."'";
		} else if ($reason == FileException::REMOVE_ERROR) {
			$message = "Failed to remove file at path '".$path."'";
		} else if ($reason == FileException::FILE_NOT_OPEN_ERROR) {
			$message = "File at '".$path."' is not open";
		} else if ($reason == FileException::READ_ERROR) {
			$message = "Failed to read file at '".$path."'";
		}
		parent::__construct($message, $reason);
	}

}
