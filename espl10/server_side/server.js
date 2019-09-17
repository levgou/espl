// const PythonShell = require('python-shell');
let {PythonShell} = require('python-shell')

function sendMail(name, mail, msg) {
    console.log(PythonShell);
    let options = {
        mode: 'text',
        pythonPath: '/usr/bin/python',
        pythonOptions: ['-u'],
        scriptPath: './server_side',
        args: [name, mail, msg] //these are the arguments that the python script will receive
    };

    PythonShell.run('mail_sender.py', options, function (err, results) {
        cosole.log(err);
        // results is an array consisting of messages collected during execution
        console.log('results: %j', results);
    });
}

const express = require('express');
const app = express();
const port = 3000;

let bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', (req, res) => res.send('Hello World!'));
app.post('/sendmail', function(req, res) {
    let body = req.body
    console.log(req.body);
    sendMail(body.txtName, body.txtEmail, body.txtMsg);
   res.sendStatus(200);
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`));
