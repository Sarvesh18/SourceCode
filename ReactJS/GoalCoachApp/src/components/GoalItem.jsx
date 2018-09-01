import React, {Component} from 'react';
import {connect} from 'react-redux';
import {goalRef, completeRef} from 'firebase';


console.log('GoalItem');
class GoalItem extends Component {
  completeGoal() {
    const {email} =this.props;
    const {serviceKey, title} = this.props.goal;
    console.log('GoalItem completeGoal()',email,serviceKey,title);
    goalRef.child(serviceKey).remove();
    completeRef.push({email:email,title:title});
  }
  render() {
    console.log("GoalItem render goal",this.props.goal);
    const {email,title}=this.props.goal;
    return(
      <div>
        <strong>{title}</strong>
        &nbsp;by&nbsp;
        <span>{email}</span>
        <button type='button' className="btn btn-sm btn-primary"
          onClick={()=> this.completeGoal()
        }>
          Complete
        </button>
      </div>
    )
  }
}

function mapStateToProps(state) {
  console.log('GoalItem mapStateToProps state',state);
  const {email} = state.user;
  return{
    email: email
  }
}

export default connect(mapStateToProps,null)(GoalItem);
