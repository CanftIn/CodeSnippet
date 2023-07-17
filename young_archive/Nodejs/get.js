var http = require('http');

http.get('http://www.baidu.com', function(req, res){
    var html = '';
    req.on('data', function(data){
        html += data;
    });
    req.on('end', function(){
        console.info(html);
    })
})