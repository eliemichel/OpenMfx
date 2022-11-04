function getTextNodes(node) {
    var textNodes = [];

    function aux(node) {
        if (node.nodeType == 3) {
            textNodes.push(node);
        } else {
            for (var i = 0, len = node.childNodes.length; i < len; ++i) {
                aux(node.childNodes[i]);
            }
        }
    }

    aux(node);
    return textNodes;
}

$(document).ready(function() {
	var images = $(".literate p img");
	images.after(function(i) {
		return '<div class="caption">' + this.alt + '</div>';
	})
	images.each(function(i) {
		this.parentElement.style = "margin: 1em 0";
	});

	// Fix a bug of 'lit'
	var sections_titles = $(".literate a[name] h4");
	sections_titles.each(function(i) {
		var link = this.parentElement;
		link.href = '#' + link.name;
		link.removeAttribute('name');
		$(this).replaceWith('<h2>' + $(this).html() +'</h2>')
	})

	var codeblocks = $('.literate .codeblock');
	codeblocks.each(function(i) {
		var texts = getTextNodes(this);
		for (var j = 0 ; j < texts.length ; ++j) {
			texts[j].data = texts[j].data.replaceAll('\t', '    ');
		}
	})

	// Add tags for prism.js
	codeblocks.children('pre').each(function(i) {
		var texts = getTextNodes(this);
		for (var j = 0 ; j < texts.length ; ++j) {
			var text = $(texts[j]);
			if (text.parents('.nocode').length == 0) {
				text.wrap('<code class="language-cpp"></code>');
			}
		}
	})
});
