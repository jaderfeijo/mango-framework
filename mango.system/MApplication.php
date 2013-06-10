<?php

	/*
	 * Copyright (c) 2011 Movinpixel Ltd. All rights reserved.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 * 3. Neither the name of the company nor the names of its contributors
	 *    may be used to endorse or promote products derived from this software
	 *    without specific prior written permission.
	 *
	 * THIS SOFTWARE IS PROVIDED BY MOVINPIXEL AND ITS CONTRIBUTORS ``AS IS'' AND
	 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	 * ARE DISCLAIMED.  IN NO EVENT SHALL MOVINPIXEL OR ITS CONTRIBUTORS BE LIABLE
	 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	 * SUCH DAMAGE.
	 */
	
	package('mango.system');
	
	import('mango.system.io.*');
	import('mango.system.html.*');
	import('mango.system.exceptions.*');
	
	/**
	 * This class holds a representation of the currently running Mango
	 * Application. It controls the execution and allows you to configure
	 * several different aspects of your Mango Application
	 *
	 * You should never create an instance of this class directly. To access
	 * the MApplication singleton instance that represents the currently
	 * running Application use MApplication::sharedApplication()
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @license MIT
	 *
	 * @package mango.system
	 *
	 */
	class MApplication extends MObject {
		
		protected static $application;
		
		/**
		 * Returns the MApplication instance that represents the currently
		 * running application
		 *
		 * @return MApplication The currently running Application instance
		 */
		public static function sharedApplication() {
			if (!MApplication::$application) {
				MApplication::$application = new MApplication();
			}
			return MApplication::$application;
		}
		
		//
		// ************************************************************
		//
		
		protected $delegate;
		protected $defaultNamespace;
		protected $rootViewController;
		
		/**
		 * @internal
		 *
		 * @return MApplication
		 */
		public function __construct(MString $delegateClass = null) {
			parent::__construct();
			
			MApplication::$application = $this;
			
			if (!$this->isRoutingEnabled()) {
				$this->enableRouting();
				
				$redirect = new MHTTPResponse(MHTTPResponse::RESPONSE_FOUND);
				$redirect->addHeader(S("Location"), MHTTPRequest()->url());
				
				MDie($redirect);
			}
			
			$this->rootViewController = null;
			
			if ($delegateClass) {
				$this->delegate = MObject::newInstanceOfClass($delegateClass);
			} else {
				$xmlManifest = simplexml_load_file("resources/manifest.xml");
				$this->delegate = MObject::newInstanceOfClass(S($xmlManifest['delegate']));
				$this->defaultNamespace = $this->parseNamespaceElement($xmlManifest);
			}
		}
		
		/******************** Protected ********************/
		
		/**
		 * @internal
		 *
		 * @return MApplicationNamespace
		 */
		public function parseNamespaceElement($namespaceElement) {
			$namespace = new MApplicationNamespace(S($namespaceElement['name']));
			$namespace->setErrorViewControllerClass(S($namespaceElement['errorClass']));
			
			foreach ($namespaceElement as $element) {
				if ($element->getName() == "controller") {
					if (is_null($element['name'])) {
						$namespace->setMainController($this->parseControllerElement($element));
					} else {
						$namespace->addController($this->parseControllerElement($element));
					}
				} else if ($element->getName() == "namespace") {
					$namespace->addChildNamespace($this->parseNamespaceElement($element));
				} else {
					throw new MParseErrorException(S("resources/manifest.xml"), null, Sf("Unknown element '%s'", $element->getName()));
				}
			}
			
			return $namespace;
		}
		
		/**
		 * @internal
		 *
		 * @return MApplicationController
		 */
		public function parseControllerElement($controllerElement) {
			$controller = new MApplicationController(S($controllerElement['class']), S($controllerElement['name']));
			
			foreach ($controllerElement as $attributeElement) {
				if ($attributeElement->getName() == "parameters") {
					foreach ($attributeElement as $parameterElement) {
						$required = true;
						if (isset($parameterElement['required'])) {
							$required = MNumber::parseBool((string)$parameterElement['required'])->boolValue();
						}

						if ($parameterElement['type'] == "String") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::StringType, $required));
						} else if ($parameterElement['type'] == "Integer") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::IntegerType, $required));
						} else if ($parameterElement['type'] == "Float") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::FloatType, $required));
						} else if ($parameterElement['type'] == "Boolean") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::BooleanType, $required));
						} else if ($parameterElement['type'] == "Date") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::DateType, $required));
						} else if ($parameterElement['type'] == "Binary") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::Binary, $required));
						} else if ($parameterElement['type'] == "Array") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::ArrayType, $required));
						} else if ($parameterElement['type'] == "Dictionary") {
							$controller->addParameter(new MApplicationControllerParameter(S($parameterElement['name']), MApplicationControllerParameter::DictionaryType, $required));
						} else {
							throw new MParseErrorException(S("resources/manifest.xml"), null, Sf("Unknown type '%s'", $parameterElement['type']));
						}
					}
				} else if ($attributeElement->getName() == "accept") {
					$acceptedMethod = new MApplicationControllerAcceptedMethod(S($attributeElement['method']));
					foreach ($attributeElement as $acceptElement) {
						if ($acceptElement->getName() == "content-types") {
							foreach ($acceptElement as $contentTypeElement) {
								$acceptedMethod->addContentType(S($contentTypeElement));
							}
						} else if ($acceptElement->getName() == "fields") {
							foreach ($acceptElement as $fieldElement) {
								$required = true;
								if (isset($fieldElement['required'])) {
									$required = MNumber::parseBool((string)$fieldElement['required'])->boolValue();
								}
								
								if ($fieldElement['type'] == "String") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::StringType, $required));
								} else if ($fieldElement['type'] == "Integer") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::IntegerType, $required));
								} else if ($fieldElement['type'] == "Float") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::FloatType, $required));
								} else if ($fieldElement['type'] == "Boolean") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::BooleanType, $required));
								} else if ($fieldElement['type'] == "Date") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::DateType, $required));
								} else if ($fieldElement['type'] == "Binary") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::BinaryType, $required));
								} else if ($fieldElement['type'] == "Array") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::ArrayType, $required));
								} else if ($fieldElement['type'] == "Dictionary") {
									$acceptedMethod->addField(new MApplicationControllerField(S($fieldElement['name']), MApplicationControllerField::DictionaryType, $required));
								} else {
									throw new MParseErrorException(S("resources/manifest.xml"), null, Sf("Unknown type '%s'", $fieldElement['type']));
								}
							}
						} else {
							throw new MParseErrorException(S("resources/manifest.xml"), null, Sf("Unknown element '%s'", $acceptElement->getName()));
						}
					}
					$controller->addAcceptedMethod($acceptedMethod);
				} else {
					throw new MParseErrorException(S("resources/manifest.xml"), null, Sf("Unknown element '%s'", $attributeElement->getName()));
				}
			}
			
			if ($controller->acceptedMethods()->count() <= 0) {
				$controller->addAcceptedMethod(new MApplicationControllerAcceptedMethod(S("GET")));
			}
			
			return $controller;
		}
		
		/**
		 * @internal
		 *
		 * @return bool
		 */
		protected function isRoutingEnabled() {
			// TODO: In the future maybe this check could be more sophisticated than this
			// and actually look inside the configuration file to check if everything is
			// setup properly
			return MFile::fileExists('.htaccess');
		}
		
		/**
		 * @internal
		 *
		 * @return void
		 */
		protected function enableRouting() {
			MLog("[EnableRouting]: Creating '.htaccess' file for URL routing…");
		
			$fileStream = new MFileOutputStream(new MFile(S(".htaccess")));
			$writer = new MStreamWriter($fileStream);
			$writer->writeLine(S("# Mango URL Routing Code"));
			$writer->writeLine(S("RewriteEngine On"));
			$writer->writeLine(S("RewriteRule . index.php"));
			$writer->close();
			
			MLog("[EnableRouting]: File created");
		}
		
		
		/**
		 * @internal
		 *
		 * Returns the root view controller for this current instance of the application.
		 * The root view controller is returned depending on which parameters are called.
		 * The Application class parses the request URL and breaks down the different elements
		 * into controller url, and parameters. This determines which view controller should
		 * be instanced and called. The appropriate view controller is instanced according to
		 * those parameters and returned by this method.
		 *
		 * @return MViewController The root view controller for this instance of the application
		 */
		protected function rootViewController() {
			if (!$this->rootViewController) {
				$this->rootViewController = $this->defaultNamespace()->viewControllerForPath(MHTTPRequest()->arguments());
			}
			return $this->rootViewController;
		}
		
		/******************** Properties ********************/
		
		/**
		 *
		 * @return MApplicationNamespace
		 */
		public function defaultNamespace() {
			if (!$this->defaultNamespace) {
				$this->defaultNamespace = new MApplicationNamespace(S(""));
			}
			return $this->defaultNamespace;
		}
		
		/**
		 * Returns the Application Delegate instance used by this application
		 *
		 * @return MApplicationDelegate The Application Delegate instance for this
		 * application
		 */
		public function delegate() {
			return $this->delegate;
		}
		
		/******************** Methods ********************/
		
		/**
		 * This function needs to be called by your top-level script. This is the
		 * entry point for your application's execution
		 *
		 * When you call this function, the Mango environment parses all the information
		 * it needs, sets itself up and boots up its classes
		 *
		 * This is also where routing occours. The system finds the controller class for
		 * the specified URL and loads it
		 *
		 * The system takes care of handling top-level errors that may occour. For example,
		 * if the URL requested by the user has no registered controllers, the system returns
		 * a 404 View to the user and responds with the appropriate HTTP code.
		 *
		 * The same thing happens if an exception is thrown and not caught or if another error
		 * occours in the execution of your code. The system catches the error, outputs the
		 * appropriate error information to the error log and returns an 500 Internal Server
		 * Error view to the client
		 *
		 * @return void
		 */
		public function run() {
			try {
				$this->delegate->applicationDidLoad();
				$viewController = $this->rootViewController();
				
				MSendResponse(new MHTTPViewControllerResponse($viewController));
			} catch (MBadRequestException $e) {
				$viewController = MObject::newInstanceOfClassWithParameters($this->defaultNamespace()->errorViewControllerClass(), A(
					MHTTPResponse::RESPONSE_BAD_REQUEST, N(MHTTPResponse::RESPONSE_BAD_REQUEST), S("Bad Request"), $e->description()
				));
				
				logException($e);
				
				MSendResponse(new MHTTPViewControllerResponse($viewController));
			} catch (MException $e) {
				$viewController = MObject::newInstanceOfClassWithParameters($this->defaultNamespace()->errorViewControllerClass(), A(
					MHTTPResponse::RESPONSE_INTERNAL_SERVER_ERROR, N(MHTTPResponse::RESPONSE_INTERNAL_SERVER_ERROR), S("Internal Server Error"), S("Sorry but the page you are looking for could not be loaded due to an internal server error")
				));
				
				logException($e);
				
				MSendResponse(new MHTTPViewControllerResponse($viewController));
			}
		}
	
	}

?>