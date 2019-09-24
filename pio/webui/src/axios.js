import axios from 'axios';

axios.defaults.baseURL = process.env.VUE_APP_AXIOS_BASE_URL || '/';
