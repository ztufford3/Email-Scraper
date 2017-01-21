var page = require('webpage').create();
var webpages = [''];
var index = 0;
var count = 0;
var emails = [];
var emailaddr;
var festival;
var limit = 0;
var args = require('system').args;

function handle_page(url) {
		page.open(url, function(status) {
		if(status === "success") {
			if(index == 0) {
				index++;
				emailaddr = args[1];
				festival = args[2];
				limit = args[3]
				page.evaluate(function(emailaddr) {
					document.getElementById('username').value=emailaddr;
					document.getElementById('password').value=;
					document.getElementById('submitBtn').click();
				}, emailaddr);
				setTimeout(function() {
					page.evaluate(function(festival) {
						document.getElementById("foldertree_INBOX.Doug." + festival).click();
					}, festival);
					setTimeout(function() {
							page.evaluate(function() {
								document.getElementById('tbody_mailindex').children[1].click();
							});

							setInterval(function() {
								var eaddress = page.evaluate(function(count) {
									var table = document.getElementById('view_body_header').children[0];
									var tableBody = table.children[0];
									var mainRow = tableBody.children[0];
									var mainBody = mainRow.children[0].children[0].children[0].children[0];
									var toRow = mainBody.children[3];
									var cell = toRow.children[1];
									var link = cell.children[0];
									var out = link.innerText;
									
									return out;
								}, 'eaddress');

								setTimeout(function() {
									page.evaluate(function() {
										document.getElementById('view_next_button').children[0].click();
									});
								}, 6400);

								emails[count] = eaddress+"\n";
								count++;
								if(count > 	limit) {
									emails[0] = ",\n"; //this just makes the csv import into Numbers a little cleaner
									console.log(emails.toString());
									phantom.exit();
								}
						}, 6600);
					}, 4000);
				}, 6000);
			}
		}
	});
}

function next_page() {
	var url = webpages[index];
	if(!url) {
		phantom.exit();
	}
	handle_page(url);
}

next_page();
