<?hh

class SourceException extends Exception {

	const int FETCH_FAILED = 1000;

	public function __construct(Source $source, int $reason) {
		$message = "Unknown exception";
		if ($reason == SourceException::FETCH_FAILED) {
			$message = "Failed to fetch source '".$source->name()."' from '".$source->url()."'";
		}
		parent::__construct($message, $reason);
	}

}

