<?hh // strict

class Console {
	
	protected static ?Console $_console = null;
	
	public static function stdout() : Console {
		if (is_null(self::$_console)) {
			self::$_console = new Console();
		}
		return self::$_console;
	}
	
	public function message(string $message) : void {
		$this->printLn($message);
	}
	
	public function warning(string $warning) : void {
		$this->printWarning($warning);
	}
	
	public function error(string $error) : void {
		$this->printError($error, false);
	}
	
	public function printError(string $error, bool $fatal = true) : int {
		if ($fatal) {
			$this->printLn("Fatal error: $error");
		} else {
			$this->printLn("Error: $error");
		}
		return 1;
	}

	public function printException(Exception $exception) : void {
		$this->printLn("An exception occured:");
		$this->printLn((string)$exception);
	}
	
	public function printWarning(string $warning) : void {
		$this->printLn("Warning: $warning");
	}
	
	public function printLn(string $line) : void {
		$this->printString("$line\n");
	}

	public function printString(string $string) : void {
		echo "$string";
	}

}

