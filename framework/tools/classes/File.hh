<?hh // strict

class File {

	const int READ_MODE = 0;
	const int WRITE_MODE = 1;
	
	protected string $_path;
	protected ?resource $_fileResource;

	public function __construct(string $path, int $mode) {
		$this->_path = $path;

		$file = null;
		if ($mode == File::READ_MODE) {
			$file = fopen($path, 'r');
		} else if ($mode == File::WRITE_MODE) {
			$file = fopen($path, 'w');
		}
		
		if ($file === null) {
			throw new FileException($path, FileException::OPENING_ERROR);
		}
		$this->_fileResource = $file;
	}

	/****************** Properties ******************/

	public function path() : string {
		return $this->_path;
	}

	public function fileResource() : ?resource {
		return $this->_fileResource;
	}

	/****************** Methods ******************/

	public function isOpen() : bool {
		if ($this->fileResource() !== null) {
			return true;
		} else {
			return false;
		}
	}

	public function readLine() : ?string {
		if ($this->isOpen()) {
			$line = fgets($this->fileResource());
			if ($line !== false) {
				return $line;
			} else {
				return null;
			}
		} else {
			throw new FileException($this->path(), FileException::FILE_NOT_OPEN_ERROR);
		}
	}

	public function eof() : bool {
		if (!$this->isOpen()) {
			throw new FileException($this->path(), FileException::FILE_NOT_OPEN_ERROR);
		}
		return feof($this->fileResource());
	}

	public function close() : void {
		if (!$this->isOpen()) {
			throw new FileException($this->path(), FileException::FILE_NOT_OPEN_ERROR);
		}
		if (!fclose($this->fileResource())) {
			throw new FileException($this->path(), FileException::CLOSING_ERROR);
		}
		$this->_fileResource = null;
	}

}
