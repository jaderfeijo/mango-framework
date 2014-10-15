<?hh

class ZipFileException extends Exception {

	const int OPENING_ERROR = 1000;
	const int EXTRACTION_ERROR = 1001;
	const int CLOSING_ERROR = 1002;

	public function __construct(string $package, string $output, int $code) {
		$message = 'Failed to ';
		if ($code == ZipFileException::OPENING_ERROR) {
			$message .= 'open';
		} else if ($code == ZipFileException::EXTRACTION_ERROR) {
			$message .= 'extract';
		} else if ($code == ZipFileException::CLOSING_ERROR) {
			$message .= 'close';
		}
		$message .= " package at '$package' with output directory '$output'";
		parent::__construct($message, $code);
	}

}
