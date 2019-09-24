import Vue from 'vue';
import Buefy from 'buefy';
import App from './App.vue';
import store from './store';
import './axios';
import './icons';
import '@/assets/css/main.scss';

Vue.config.productionTip = false;
Vue.use(Buefy, {
  defaultIconComponent: 'vue-fontawesome',
  defaultIconPack: 'fas',
});

new Vue({
  store,
  render: h => h(App),
}).$mount('#app');
