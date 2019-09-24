import Vue from 'vue';
import { library } from '@fortawesome/fontawesome-svg-core';
// internal icons
import {
  faExclamationTriangle,
  faQuoteRight,
  faCog,
  faSyncAlt,
  faList,
  faEdit,
  faPlusSquare,
  faEye,
  faEyeSlash,
} from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';

library.add(
  faExclamationTriangle,
  faQuoteRight,
  faCog,
  faSyncAlt,
  faEdit,
  faList,
  faPlusSquare,
  faEye,
  faEyeSlash
);
Vue.component('vue-fontawesome', FontAwesomeIcon);
