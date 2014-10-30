<?hh // strict

class LibraryNotFoundException extends Exception {

	const int LibraryNotFoundExceptionCode = 2000;

	protected string $_library;
	protected string $_version;

	public function __construct(string $library, string $version) {
		$message = "Could not find library '$library' version '$version'";

		parent::__construct($message, LibraryNotFoundException::LibraryNotFoundExceptionCode);

		$this->_library = $library;
		$this->_version = $version;
	}

	public function library() : string {
		return $this->_library;
	}

	public function version() : string {
		return $this->_version;
	}

}

