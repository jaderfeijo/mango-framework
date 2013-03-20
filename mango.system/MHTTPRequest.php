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
	
	/**
	 * 
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @license MIT
	 *
	 * @package mango.system
	 *
	 */
	class MHTTPRequest extends MObject {
		
		const REQUEST_METHOD_OPTIONS = "OPTIONS";
		const REQUEST_METHOD_GET = "GET";
		const REQUEST_METHOD_HEAD = "HEAD";
		const REQUEST_METHOD_POST = "POST";
		const REQUEST_METHOD_PUT = "PUT";
		const REQUEST_METHOD_DELETE = "DELETE";
		const REQUEST_METHOD_TRACE = "TRACE";
		const REQUEST_METHOD_CONNECT = "CONNECT";
		
		protected static $request;
		
		/**
		 * 
		 *
		 * @return MHTTPRequest
		 */
		public static function request() {
			if (!MHTTPRequest::$request) {
				MHTTPRequest::$request = new MHTTPRequest();
			}
			return MHTTPRequest::$request;
		}
		
		//
		// ************************************************************
		//
		
		protected $method;
		protected $contentType;
		protected $inputParameters;
		protected $inputFields;
		protected $arguments;
		protected $baseAddress;
		protected $relativeAddress;
		protected $baseUrl;
		protected $url;
		
		/**
		 * @internal
		 *
		 * @return MHTTPRequest
		 */
		public function __construct() {
			parent::__construct();
			
			$this->method = null;
			$this->contentType = null;
			$this->inputParameters = null;
			$this->inputFields = null;
			$this->arguments = null;
			$this->baseAddress = null;
			$this->relativeAddress = null;
			$this->baseUrl = null;
			$this->url = null;
		}
		
		/******************** Properties ********************/
		
		/**
		 * 
		 *
		 * @return string
		 */
		public function method() {
			if (!$this->method) {
				$this->method = $_SERVER['REQUEST_METHOD'];
			}
			return $this->method;
		}
		
		/**
		 * @return MString
		 */
		public function contentType() {
			if (!$this->contentType) {
				if (isset($_SERVER['CONTENT_TYPE'])) {
					$this->contentType = S($_SERVER['CONTENT_TYPE']);
				}
			}
			return $this->contentType;
		}
		
		/**
		 * @return MDictionary
		 */
		public function inputParameters() {
			if (!$this->inputParameters) {
				$this->inputParameters = new MMutableDictionary();
				$data = $_GET;
				foreach ($data as $key => $value) {
					$this->inputParameters->setObjectForKey(S($key), $value);
				}
			}
			return $this->inputParameters;
		}
		
		/**
		 * 
		 *
		 * @return MDictionary
		 */
		public function inputFields() {
			if (!$this->inputFields) {
				$this->inputFields = new MMutableDictionary();
				$data = $_POST;
				if (!$data) {
					$data = array();
					parse_str(file_get_contents("php://input"), $data);
				}
				foreach ($data as $key => $value) {
					$this->inputFields->setObjectForKey(S($key), $value);
				}
			}
			return $this->inputFields;
		}
		
		/**
		 * 
		 *
		 * @return MArray
		 */
		public function arguments() {
			if (!$this->arguments) {
				if (!$this->relativeAddress()->isEmpty()) {
					$argsString = $this->relativeAddress()->componentsSeparatedByString(S("?"), false)->objectAtIndex(0);
					$this->arguments = $argsString->componentsSeparatedByString(S("/"), false);
				} else {
					$this->arguments = new MArray();
				}
			}
			return $this->arguments;
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function baseAddress() {
			if (!$this->baseAddress) {
				$this->baseAddress = S($_SERVER['SCRIPT_NAME'])->stringByReplacingOccurrencesOfString(S("index.php"), S(""))->stringByTrimmingCharactersInSet(S("/"));
			}
			return $this->baseAddress;
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function relativeAddress() {
			if (!$this->relativeAddress) {
				$this->relativeAddress = S($_SERVER['REQUEST_URI'])->stringByReplacingOccurrencesOfString($this->baseAddress(), S(""))->stringByTrimmingCharactersInSet(S("/"));
			}
			return $this->relativeAddress;
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function baseUrl() {
			if (!$this->baseUrl) {
				$url = new MMutableString();
				if (!empty($_SERVER['HTTPS'])) {
					$url->appendString(S("https://"));
				} else {
					$url->appendString(S("http://"));
				}
				$url->appendString(S($_SERVER['HTTP_HOST']));
				$this->baseUrl = $url;
			}
			return $this->baseUrl;
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function url() {
			if (!$this->url) {
				$this->url = $this->baseUrl()->stringByAppendingPathComponent($this->baseAddress())->stringByAppendingPathComponent($this->relativeAddress());
			}
			return $this->url;
		}
		
	}

?>