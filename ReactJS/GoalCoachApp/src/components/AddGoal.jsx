import React, {Component} from 'react';
import {goalRef} from '../firebase';
import {connect} from 'react-redux';

console.log('AddGoal');
class AddGoal extends Component {
  constructor(props) {
    super(props);
    this.state={
      title: ''
    }
  }
  addGoal() {
    const {title} = this.state;
    const {email} = this.props;
    console.log("AddGoal state",this.state);
    console.log("AddGoal props",this.props);
    goalRef.push({email: email,title:title});
  }
  render () {
    return (
        <form className="form-inline">
          <input className="form-control" style={{marginRight: '5px',marginTop: '10px'}} type="text" placehoder="Enter"
            onChange={event =>
              this.setState({title:event.target.value})
            }/>
          <button className="btn btn-success" style={{marginLeft: '5px',marginTop: '10px'}} type="button"
            onClick={()=>
              this.addGoal()
            }>
            Submit
          </button>
        </form>
    )
  }
}
function mapStateToProps(state) {
  console.log('AddGoal mapStateToProps state',state);
  const {email} = state.user;
  return {
    email: email
  }
}
export default connect(mapStateToProps,null)(AddGoal);
