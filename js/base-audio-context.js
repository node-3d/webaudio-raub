'use strict';

const util  = require('util');

const EventEmitter = require('events');

const { BaseAudioContext } = require('../core');


BaseAudioContext.prototype.__proto__ = EventEmitter.prototype;

class JsBaseAudioContext extends BaseAudioContext {
	
	constructor(ctx) {
		
		super(ctx);
		
	}
	
	
	addEventListener(type, cb) {
		this.on(type, cb);
	}
	
	
	removeEventListener(type, cb) {
		this.removeListener(type, cb);
	}
	
	
	dispatchEvent(e) {
		this.emit(e.type || 'unknown', e);
	}
	
	
	on(name, cb) {
		
		super.on(name, cb);
		
		if (name === 'load' && this._data) {
			cb.call(this);
		}
		
	}
	
	
	once(name, cb) {
		
		if (name === 'load' && this._data) {
			cb.call(this);
		} else {
			super.once(name, cb);
		}
		
	}
	
	get onerror() { return this.listeners('error'); }
	set onerror(cb) { this.on('error', cb); }
	
	[util.inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'BaseAudioContext {}';
	}
	
}


module.exports = JsBaseAudioContext;
