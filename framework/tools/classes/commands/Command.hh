<?hh // strict

class Command {

	const int ERR_TOO_FEW_ARGUMENTS = 100;
	const int ERR_TOO_MANY_ARGUMENTS = 101;
	const int ERR_COMMAND_NOT_FOUND = 102;
	const int ERR_COMMAND_NOT_IMPLEMENTED = 103;

	const int R_INVALID_PARAMETERS = 1;

	protected string $_name;
	protected ?string $_description;
	protected ?Vector<string> $_requiredArguments;
	protected ?Vector<string> $_optionalArguments;
	protected ?Command $_parent;

	public function __construct(string $name, ?string $description = null, ?Vector<string> $requiredArguments = null, ?Vector<string> $optionalArguments = null) {
		$this->_name = $name;
		$this->_description = $description;
		$this->_requiredArguments = $requiredArguments;
		$this->_optionalArguments = $optionalArguments;
		$this->_parent = null;
	}
	
	/******************* Properties *******************/
	
	public function name(): string {
		return $this->_name;
	}
	
	public function description(): ?string {
		return $this->_description;
	}
		
	public function requiredArguments(): ?Vector<string> {
		return $this->_requiredArguments;
	}
	
	public function optionalArguments(): ?Vector<string> {
		return $this->_optionalArguments;
	}
	
	public function parent(): ?Command {
		return $this->_parent;
	}

	/******************* Dynamic Properties *******************/
	
	public function totalRequiredArguments(): int {
		$requiredArguments = $this->requiredArguments();
		if ($requiredArguments !== null) {
			return $requiredArguments->count();
		} else {
			return 0;
		}
	}
	
	public function totalOptionalArguments(): int {
		$optionalArguments = $this->optionalArguments();
		if ($optionalArguments !== null) {
			return $optionalArguments->count();
		} else {
			return 0;	
		}
	}
	
	public function totalArguments(): int {
		return $this->totalRequiredArguments() + $this->totalOptionalArguments();
	}
	
	public function fullCommandString(): string {
		$parent = $this->parent();
		if ($parent !== null) {
			return $parent->fullCommandString().' '.$this->name();
		} else {
			return $this->name();
		}
	}

	public function fullArgumentsString(): string {
		$args = '';
		
		$requiredArguments = $this->requiredArguments();	
		if ($requiredArguments !== null) {
			foreach ($requiredArguments as $arg) {
				$args .= '['.$arg.'] ';
			}
		}

		$optionalArguments = $this->optionalArguments();
		if ($optionalArguments !== null) {
			foreach ($optionalArguments as $arg) {
				$args .= '{'.$arg.'} ';
			}
		}

		return $args;
	}

	public function usageString(): string {
		return $this->fullCommandString().' '.$this->fullArgumentsString()."\n    ".$this->description();
	}

	/******************* Protected Methods *******************/
	
	protected function setParent(?Command $parent): void {
		$this->_parent = $parent;
	}
	
	/******************* Methods *******************/
	
	public function run(Vector<string> $args): int {
		if ($args->count() < $this->totalRequiredArguments()) {
			return $this->usage(self::ERR_TOO_FEW_ARGUMENTS);
		} else if ($args->count() > $this->totalArguments()) {
			return $this->usage(self::ERR_TOO_MANY_ARGUMENTS);
		} else {
			return $this->execute($args);
		}
	}
	
	public function usage(int $errorCode): int {
		$cmd = $this->fullCommandString();
		$message = 'unknown parameters!';
		
		if ($errorCode == self::ERR_TOO_FEW_ARGUMENTS) {
			$message = 'too few arguments!';
		} else if ($errorCode == self::ERR_TOO_MANY_ARGUMENTS) {
			$message = 'too many arguments!';
		} else if ($errorCode == self::ERR_COMMAND_NOT_FOUND) {
			$message = 'command not found!';
		} else if ($errorCode == self::ERR_COMMAND_NOT_IMPLEMENTED) {
			$message = 'command not implemented!';
		}

		$usage = $this->usageString();
		
		Console::stdout()->printLn("$cmd: $message");
		Console::stdout()->printLn("usage: $usage");

		return self::R_INVALID_PARAMETERS;
	}
	
	public function execute(Vector<string> $args): int {
		return $this->usage(self::ERR_COMMAND_NOT_IMPLEMENTED);
	}

}

