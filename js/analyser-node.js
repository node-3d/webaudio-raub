'use strict';

const util  = require('util');

const { AnalyserNode } = require('../core');
const AudioNode = require('./audio-node');


AnalyserNode.prototype.__proto__ = AudioNode.prototype;

class JsAnalyserNode extends AnalyserNode {
	
	constructor(ctx, _opts = {}) {
		
		const opts = {
			fftSize : 2048,
			maxDecibels : -30,
			minDecibels : -100,
			smoothingTimeConstant : 0.8,
			..._opts,
		};
		
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
	
	
	load(data) { this._load(data); }
	
	
	get complete() { return this._data !== null; }
	
	get data() { return this._data; }
	
	
	get naturalWidth() { return this.width; }
	get naturalHeight() { return this.height; }
	
	get wh() { return [this.width, this.height]; }
	get size() { const [width, height] = this.wh; return { width, height }; }
	
	
	get src() { return this._src; }
	
	set src(v) {
		
		// The same - do nothing
		if (v === this._src) {
			return;
		}
		
		
		this._error = null;
		this._data = null;
		this._src = v;
		this._isDataUri = false;
		
		
		// Empty - do nothing
		if ( ! this._src ) {
			return this._unload();
		}
		
		
		// Data URI
		if (/^data:/.test(this._src)) {
			
			this._isDataUri = true;
			const [head, body] = this._src.split(',');
			const isBase64 = head.indexOf('base64') > -1;
			const data = isBase64 ? Buffer.from(body, 'base64') : Buffer.from(unescape(body));
			console.log('image.js', 'this', this, this._load, this.save, this.width);
			this._load(data);
			return;
			
		}
		
		
		// Remote image
		if (/^https?:\/\//i.test(this._src)) {
			
			download(this._src).then(
				data => this._load(data),
				err => this.emit('error', err)
			);
			
			return;
			
		}
		
		
		// Filesystem image
		fs.readFile(this._src, (err, data) => {
			if (err) {
				return this.emit('error', err);
			}
			this._load(data);
		});
		
	}
	
	
	get onerror() { return this.listeners('error'); }
	set onerror(cb) { this.on('error', cb); }
	
	get onload() { return this.listeners('load'); }
	set onload(cb) { this.on('load', cb); }
	
	
	[util.inspect.custom]() { return this.toString(); }
	
	toString() {
		
		if ( ! this.src ) {
			return 'AnalyserNode { EMPTY }';
		}
		
		const src = this._isDataUri ? `${this.src.slice(0, 32)}...` : this.src;
		
		if (this._error ) {
			return `AnalyserNode { ERROR, ${src} }`;
		}
		
		if ( ! this._data ) {
			return `AnalyserNode { LOADING, ${src} }`;
		}
		
		return `AnalyserNode { ${this.width}x${this.height} ${src} }`;
		
	}
	
}


module.exports = JsAnalyserNode;
