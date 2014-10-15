<?hh

class DirectoryException extends Exception {

	const int READ_ERROR = 1000;
	const int CREATE_ERROR = 1001;
	const int REMOVE_ERROR = 1002;

	public function __construct(string $path, int $code) {
		$message = 'Failed to ';
		if ($code == DirectoryException::READ_ERROR) {
			$message .= 'read';
		} else if ($code == DirectoryException::CREATE_ERROR) {
			$message .= 'create';
		} else if ($code == DirectoryException::REMOVE_ERROR) {
			$message .= 'remove';
		}
		$message .= " directory at path '$path'";
		parent::__construct($message, $code);
	}

}

