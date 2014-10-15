<?hh

class DownloadErrorException extends Exception {

	const DOWNLOAD_INIT_FAILED = 1000;
	const DOWNLOAD_OPT_FAILED = 1001;
	const DOWNLOAD_FAILED = 1002;

	public function __construct(string $url, int $reason) {
		$message = 'Failed to ';
		if ($reason == DownloadErrorException::DOWNLOAD_INIT_FAILED) {
			$message .= 'initialise';
		} else if ($reason == DownloadErrorException::DOWNLOAD_OPT_FAILED) {
			$message .= 'set option for';
		} else if ($reason == DownloadErrorException::DOWNLOAD_FAILED) {
			$message .= 'execute';
		}
		$message .= " download of URL '$url'!";
		parent::__construct($message, $reason);
	}

}

