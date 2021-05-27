var map = document.querySelector('#mapF')
var paths = map.querySelectorAll('.mapFR_image a')
var links = map.querySelectorAll('.mapFR_list a')

if(NodeList.prototype.forEach===undefined){
	NodeList.prototype.forEach=function(callback){
		[].forEach.call(this,callback)
	}
}

var activeArea = function(id){
	map.querySelectorAll('.is-active2').forEach(function (item) {
		item.classList.remove('is-active2')
	})
	if(id !== undefined){
		document.querySelector('#LFR-'+ id).classList.add('is-active2')
		document.querySelector('#FR-'+ id).classList.add('is-active2')
	}

}

paths.forEach(function (path) {
	path.addEventListener('mouseenter', function() {
	var id = this.id.replace('FR-','')
	activeArea(id)
	})
	})

links.forEach(function(link){
		link.addEventListener('mouseenter', function() {
		var id = this.id.replace('LFR-','')
			activeArea(id)

		})

	})
map.addEventListener('mouseover', function() {
	activeArea()
})
