import  React, {Component} from 'react';
import "../style/style.css";

//import {Link} from 'react-router-dom';

class Sign extends Component {
  constructor(props) {
    super(props);
    this.state = {
      username: '',
      password: '',
      error: ''
    }
    this.inpEmail = React.createRef();
    this.inpPass = React.createRef();    
  }

  signIn() {
    //event.preventDefault();

    const {email,password} = this.state;
    console.log('signin()');
    console.log('',this.inpEmail,'',this.inpEmail.current);
    //this.inpEmail.current.focus();
    //this.inpPass.current.focus();
  }

  signUp() {
    const {email,password} = this.state;
    console.log('signup()');
  }
  
  render() {
    {console.log('Signin')}
    return (
      <div className="sign">
        <ul className="nav nav-tabs">
          <li style={{width:"50%"}}><a data-toggle="tab" href="#signup">Sign Up</a></li>
          <li style={{width:"50%"}} className="active"><a data-toggle="tab" href="#signin">Sign In</a></li>
        </ul>
        <div className="tab-content">
          <div id="signin" className="tab-pane fade in active">
            <h3>Sign In</h3>
            <form onSubmit={event=>{event.preventDefault();}}>

              <div className="input-group has-success has-feedback">
                <span className="input-group-addon"><i className="glyphicon glyphicon-user"></i></span>
                <input type="email" className="form-control" placeholder="Username or Email" 
                  ref={this.inpEmail}
                  required
                  onChange={event => this.setState({email: event.target.value})
                }/>
                <span className="glyphicon glyphicon-ok form-control-feedback"></span>
              </div>
              
              <div className="input-group has-success has-feedback">
                <span className="input-group-addon"><i className="glyphicon glyphicon-lock"></i></span>
                <input type="password" className="form-control" placeholder="Password"
                  ref={this.inpPass}
                  required
                  onChange={event => this.setState({password: event.target.value})
                }/>
                <span className="glyphicon glyphicon-ok form-control-feedback"></span>
              </div>
              {
                  //has-success
                  //<span className="glyphicon glyphicon-ok form-control-feedback"></span>
                  //has-warning
                  //<span className="glyphicon glyphicon-warning-sign form-control-feedback"></span>
                  //has-error
                  //<span className="glyphicon glyphicon-remove form-control-feedback"></span>
              }



              <div className="input-group">
                <input type="checkbox"/>
                <label><span className="input-group-addon"> Remember me</span></label>
              </div>
              
              <p><a>Forget your password ?</a></p>

              <button type="submit" className="btn btn-success" 
                onClick={() => this.signIn()}>Sign In</button>
            </form>

            <div>
              T E S T
              <form onSubmit={event=>{event.preventDefault(); console.log('testform'); }}>
              <input type="email" required placeholder='Email' />
              </form>
              
            </div>

            <hr/>
              <p>Or connect with:</p>
              <button type="button" className="btn btn-default"
                  onClick={() => this.sign()}>Facebook</button>
              <button type="button" className="btn btn-success"
                  onClick={() => this.sign()}>Google</button>
              <button type="button" className="btn btn-danger"
                  onClick={() => this.sign()}>LinkedIn</button>
              <button type="button" className="btn btn-default"
                  onClick={() => this.sign()}>Github</button>
              <p>By signing up, you agree to our <a>Terms of Service</a> and <a>Privacy Policy</a>.</p>
            <hr/>

          </div>
          
          <div id="signup" className="tab-pane fade">
            <h3>Sign Up</h3>
            <form>

              <div className="input-group">
                <span className="input-group-addon"><i className="glyphicon glyphicon-user"></i></span>
                <input type="email" className="form-control" placeholder="First and Last Name" 
                  onChange={event => this.setState({name: event.target.value})
                }/>
              </div>

              <div className="input-group">
                <span className="input-group-addon"><i className="glyphicon glyphicon-envelope"></i></span>
                <input type="email" className="form-control" placeholder="Email" 
                  onChange={event => this.setState({email: event.target.value})
                }/>
              </div>

              <div className="input-group">
                <span className="input-group-addon"><i className="glyphicon glyphicon-lock"></i></span>
                <input type="password" className="form-control" placeholder="Password"
                  onChange={event => this.setState({password: event.target.value})
                }/>
              </div>
            
              <button type="submit" className="btn btn-success"
                onClick={() => this.signUp()}>Sign Up</button>
            </form>
            <hr/>
              <p>Or connect with:</p>
              <button type="button" className="btn btn-default"
                  onClick={() => this.sign()}>Facebook</button>
              <button type="button" className="btn btn-success"
                  onClick={() => this.sign()}>Google</button>
              <button type="button" className="btn btn-danger"
                  onClick={() => this.sign()}>LinkedIn</button>
              <button type="button" className="btn btn-default"
                  onClick={() => this.sign()}>Github</button>
              <p>By signing up, you agree to our <a>Terms of Service</a> and <a>Privacy Policy</a>.</p>
            <hr/>
 
          </div>
        </div>
        {
          //<Link to={'/sign'}>Instead</Link>
        }
        <div>{this.state.error}</div>
      </div>
    );
  }
}

export default Sign;
